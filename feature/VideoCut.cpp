
#include <iostream>
#include <fstream>
#include <codecvt>
#include <locale>
#include <string>
#include <cstdlib>

extern "C" {
    #include <libavformat/avformat.h>
    #include <libavcodec/avcodec.h>
    #include <libavutil/opt.h>
    #include <libavutil/timestamp.h>
    #include <libavutil/mathematics.h>
    #include <libavutil/rational.h>
}

#include <sys/stat.h> // mkdir

#include "../Beyond.h"
#include "../Parse.h"

typedef struct SFileContext{
    AVFormatContext* fmtContext;
    AVCodecParameters* codecParams;
    AVCodec* codec;
    AVCodecContext* codecContext;
    int v_index;
    int a_index;
} SFileContext;

struct SRecord{
    int64_t index;
    int64_t startTime;
    int64_t endTime;
};

static SFileContext input,output;

static AVOutputFormat *ofmt;

static void release() {

    if (input.fmtContext != NULL){
        avformat_close_input(&input.fmtContext);
        avformat_free_context(input.fmtContext);
    }
    
        
    if (output.fmtContext && !(output.fmtContext->flags & AVFMT_NOFILE))
        avio_closep(&output.fmtContext->pb);
    if (input.codecContext != NULL){
        avcodec_close (input.codecContext);
    }
}

static void logPacket(const AVFormatContext *fmt_ctx, const AVPacket *pkt, const char *tag)
{
    AVRational *time_base = &fmt_ctx->streams[pkt->stream_index]->time_base;
    std::cout<< "["<<tag<<"] :" << " pts : " <<pkt->pts<<" dts : "<<pkt->dts<<" duration : " <<pkt->duration <<std::endl;
    // printf("%s: pts:%s pts_time:%s dts:%s dts_time:%s duration:%s duration_time:%s stream_index:%d\n",
    //        tag,
    //        av_ts2str(pkt->pts), av_ts2timestr(pkt->pts, time_base),
    //        av_ts2str(pkt->dts), av_ts2timestr(pkt->dts, time_base),
    //        av_ts2str(pkt->duration), av_ts2timestr(pkt->duration, time_base),
    //        pkt->stream_index);
}



static int createOutput (const char* fileName){
    output.fmtContext = NULL;
    output.v_index = output.a_index = -1;
    

    if (avformat_alloc_output_context2 (&output.fmtContext, NULL,NULL, fileName) < 0)
    {
        std::cout << "Could not create File"<<std::endl;
        return -1;
    }

 
    for (unsigned index =0; index <input.fmtContext->nb_streams; index++)
    {
        if (index !=input.v_index && index!= input.a_index)
            continue;
        AVStream* inStream = input.fmtContext->streams[index];
        input.codecContext = inStream->codec;
        AVStream* outStream = avformat_new_stream (output.fmtContext, input.codecContext->codec);

        if (!outStream)
        {
            std::cout << "Failed to allocate output stream"<<std::endl;
            return -2;
        }
        output.codecContext = outStream->codec;
        if (avcodec_copy_context(output.codecContext, input.codecContext) < 0)
        {
            std::cout << "Error occurred while copying context"<<std::endl;
            return -3;
        }
        output.codecContext->codec_tag = 0;

        if (output.fmtContext->oformat->flags & AVFMT_GLOBALHEADER)
        {
            output.codecContext->flags |= AV_CODEC_FLAG_GLOBAL_HEADER;
        }
    }

    av_dump_format (output.fmtContext, 0, fileName, 1);

    if (!(output.fmtContext->oformat->flags & AVFMT_NOFILE))
    {
        if (avio_open(&output.fmtContext->pb, fileName, AVIO_FLAG_WRITE) < 0)
        {
            std::cout<<"Failed to create output file"<<std::endl;
            return -4;
        }
    }

    if (avformat_write_header(output.fmtContext, NULL) < 0)
    {
        std::cout<<"Failed writing header into output file"<<std::endl;
        return -5;
    }

    return 0;
}
static int openCut(){
    AVPacket pkt;
    
    while (1){
            AVStream *inStream, *outStream;
            if (av_read_frame(input.fmtContext, &pkt) == AVERROR_EOF){
                std::cout <<"End of Frame"<<std::endl;
                break;
            }

            if (pkt.stream_index != input.v_index &&
                pkt.stream_index != input.a_index)
                {
                    av_free_packet(&pkt);
                    continue;
                }
        
            inStream = input.fmtContext->streams[pkt.stream_index];
            outStream = output.fmtContext->streams[pkt.stream_index];


            av_packet_rescale_ts (&pkt, inStream->time_base, outStream->time_base);

            if (av_interleaved_write_frame (output.fmtContext, &pkt) < 0)
            {
                std::cout << "Error occurred when writing packet"<<std::endl;
                break;
            }
        }
        av_write_trailer(output.fmtContext);
}
static int openFrame (){
    AVFrame* frame = av_frame_alloc();
    if (!frame){
        std::cout << "Couldnt allocate frame "<<std::endl;
        return -1;
    }

    AVPacket* packet = av_packet_alloc();
    if (!packet){
        std::cout << "Couldnt allocate packet "<<std::endl;
        return -2;
    }

    int response;

    /**
     * Packetizing
    */
    while (av_read_frame(input.fmtContext, packet) >= 0){
        if (packet->stream_index != input.v_index){
            continue;
        }
        response = avcodec_send_packet (input.codecContext, packet);
        if (response < 0){
            std::cout << "Failed to send packet "<<std::endl;
            return -3;
        }
        response = avcodec_receive_frame (input.codecContext, frame);
        if (response == AVERROR(EAGAIN) || response == AVERROR_EOF){
            continue;
        }
        else if (response <0){
            std::cout << "Failed to receive packet "<<std::endl;
        }

        av_packet_unref (packet);
        int i =0;
    }

    unsigned char* data = new unsigned char [frame->width * frame->height *3];
    for (int x = 0; x <frame->width; x++){
        for (int y=0; y< frame->height; y++){
            data[ y * frame->width * 3 + x *3    ] = 0xff; //Red
            data[ y * frame->width * 3 + x *3 + 1] = 0x00; //B
            data[ y * frame->width * 3 + x *3 + 2] = 0x00; //Green
        }
    }
    
    av_frame_free(&frame);
    av_packet_free (&packet);
}

static int openCodec (){
    input.codecContext = avcodec_alloc_context3(input.codec);
    if (!input.codecContext){
        std::cout << "Cant find codec Context"<<std::endl;
    }

    if (avcodec_parameters_to_context (input.codecContext, input.codecParams) <0){
        std::cout <<"Could not open param"<<std::endl;
    }
    
    if (avcodec_open2 (input.codecContext, input.codec, NULL) < 0){
        std::cout<<"Could not open codec"<<std::endl;
    }
}

static int openInput (const char* fileName){

    input.fmtContext = nullptr;
    input.v_index = input.a_index = -1;
    
    av_register_all();

    input.fmtContext = avformat_alloc_context();
    if (!input.fmtContext){
        std::cout << "Couldnt create AVFormatContext"<<std::endl;
        return -1;
    }



    if (avformat_open_input(&input.fmtContext, fileName, NULL, NULL) < 0){
        std::cout << "Could not Open File"<<std::endl;
        return -1;
    }

    if (avformat_find_stream_info(input.fmtContext, NULL) < 0)
    {
        std::cout << "Failed to retrive input stream info"<<std::endl;
        return -2;
    }

    av_dump_format(input.fmtContext, 0, fileName, 0);

    for (unsigned int index=0; index < input.fmtContext->nb_streams; index++)
    {
        input.codecContext = input.fmtContext->streams[index]->codec;
        
        if (input.codecContext->codec_type == AVMEDIA_TYPE_VIDEO && input.v_index < 0){
            std::cout << "------ Video info --------"<<std::endl;
            std::cout << "codec_id : "<<input.codecContext->codec_id<<std::endl;
            std::cout << "bitrate : "<<input.codecContext->bit_rate<<std::endl;
            std::cout << "width : "<<input.codecContext->width<<std::endl;
            input.v_index = index;
        }

        else if (input.codecContext->codec_type == AVMEDIA_TYPE_AUDIO && input.a_index < 0){
            std::cout << "------ Audio info --------"<<std::endl;
            std::cout << "codec_id : "<<input.codecContext->codec_id<<std::endl;
            std::cout << "bitrate : "<<input.codecContext->bit_rate<<std::endl;
            std::cout << "sample_rate : "<<input.codecContext->sample_rate<<std::endl;
            std::cout << "number of channels "<<input.codecContext->channels<<std::endl;
            input.a_index = index;
        }

        
    }

    if ((input.v_index < 0) && (input.a_index <0)){
        std::cout << "Failed to retrieve input"<<std::endl;
    }

    

    return 0;
}


std::string utf16_to_utf8(std::u16string const& str){
    std::wstring_convert<std::codecvt_utf8_utf16<char16_t, 0x10ffff, std::codecvt_mode::little_endian>, char16_t> cnv;
    std::string utf8 = cnv.to_bytes(str);
    if (cnv.converted() < str.size()){

    }
    return utf8;
}

CJob::CVideoCut::STime* CJob::CVideoCut::parsePbf(std::string path, std::string file){

    std::ifstream openFile(path+file);
    int numLine = 0;
    std::vector<std::string> number = {};
    std::vector<std::string> name = {};
    std::string line;
    std::string tmp;

    CJob::CVideoCut::STime* pTime;

    openFile.seekg(0, std::ios::end);
    size_t size = (size_t) openFile.tellg();

    //skip Bom
    openFile.seekg(2, std::ios::beg);
    size -= 2;

    std::u16string u16((size / 2) + 1, '\0');
    openFile.read((char*)&u16[0], size);
    std::string what = utf16_to_utf8(u16);
    std::cout<<"이거는 : "<<what<<std::endl;

    openFile.close();
    what = what.substr(what.find('\n',1));
    int equal = what.find ('=');
    int star = what.find ('*');
    while (equal != -1 && star != -1){
            line = what.substr(equal+1, star - equal - 1);
            number.push_back(line);
            tmp = what.substr (star+1, what.find('*', star+1)- (star+1));
            name.push_back(tmp);
        what = what.substr(what.find('\n',1));
        equal = what.find('=');
        star = what.find('*');
        
        
        numLine++;
    }
    pTime = (CJob::CVideoCut::STime*)malloc(sizeof(CJob::CVideoCut::STime)*numLine);
    memset(pTime, 0, sizeof(CJob::CVideoCut::STime)*numLine);
    for (int i=0; i<numLine; i++){
        pTime[i].second = (stoi(number[i]) / 1000) % 60;
        pTime[i].minute = (stoi(number[i]) / 1000) / 60;
        while (pTime[i].minute >= 60){
            pTime[i].minute -= 60;
            pTime[i].hour = +1;
        }
        pTime[i].name = name[i];
        pTime[i].value = true;
    }
    return pTime;
}
int CJob::CVideoCut::proceed (CJob* pJob, SOptionGroup* optionGroup, SFlagGroup* flagGroup){
    
    std::string path = optionGroup->workPath + "/";
    std::string folderName = "temporary";
    std::string currentTag = optionGroup->fileTag;
    int nbVideos = 0;

    int startSeconds = 3;
    int endSeconds = 8;

    std::vector <std::string> pbfList;
    std::vector <std::string> fileList;

    CJob::CSubJob* pSubJob = pJob->pSubJob;
    std::string command = "";


    if (pJob->pFileName != nullptr){
    }
    else {
        pSubJob->getDirectory(path);
    }
    pbfList = pSubJob->pbfList;
    fileList = pSubJob->fileList;

    

    

    for (int i=0; i<pbfList.size(); i++){
        STime* pTime= parsePbf(path, pbfList[i]);
        int j=0;
        while (pTime[j].value == true){
            j++;
        }
        if (j%2 != 0){
            std::cout <<"Chapters are not even number"<<std::endl;
            nbVideos = j/2;
            return -1;
        }
    }

    for (int i=0; i<1; i++){
        
        
        //복잡
        //openInput ((path+fileList[1]).c_str());
        int a = 0;
        openInput ((path+fileList[0]).c_str());
        createOutput((path+"vjfdfdc.mp4").c_str());
        //openCodec ();
        //openFrame();
        openCut();















        // av_seek_frame (input.fmtContext, -1, (startSeconds-1)*AV_TIME_BASE, AVSEEK_FLAG_ANY);
        
        // int64_t *dtsStartFrom = (int64_t*) malloc (sizeof(int64_t) * input.fmtContext->nb_streams);
        // memset (dtsStartFrom, 0 , sizeof(int64_t) * input.fmtContext->nb_streams);
        // int64_t *ptsStartFrom = (int64_t*) malloc (sizeof(int64_t) * input.fmtContext->nb_streams);
        // memset (ptsStartFrom, 0 , sizeof(int64_t) * input.fmtContext->nb_streams);

        // AVPacket pkt;

        // while (1){
        //     AVStream *inStream, *outStream;
        //     if (av_read_frame(input.fmtContext, &pkt) == AVERROR_EOF){
        //         std::cout <<"End of Frame"<<std::endl;
        //         break;
        //     }

        //     inStream = input.fmtContext->streams[pkt.stream_index];
        //     outStream = output.fmtContext->streams[pkt.stream_index];

        //     if (av_q2d (inStream->time_base)*pkt.pts > endSeconds){
        //         av_free_packet(&pkt);
        //         break;
        //     }

        //     if (dtsStartFrom[pkt.stream_index] == 0){
        //         dtsStartFrom[pkt.stream_index] = pkt.dts;
        //         std::cout <<"DTS"<<std::endl;
        //         //std::cout << "dts start from "<<av_ts2str(dtsStartFrom[pkt.stream_index])<<std::endl;
        //     }


        //     if (ptsStartFrom[pkt.stream_index] == 0){
        //         ptsStartFrom[pkt.stream_index] = pkt.dts;
        //         std::cout <<"PTS"<<std::endl;
        //         //std::cout << "pts start from "<<av_ts2str(ptsStartFrom[pkt.stream_index])<<std::endl;
        //     }

        //     /**
        //      * copy packet
        //     */
        //     pkt.pts = av_rescale_q (pkt.pts - ptsStartFrom[pkt.stream_index], inStream->time_base, outStream->time_base);
        //     pkt.dts = av_rescale_q (pkt.dts - dtsStartFrom[pkt.stream_index], inStream->time_base, outStream->time_base);

        //     if (pkt.pts < 0)
        //         pkt.pts = 0;
        //     if (pkt.dts < 0)
        //         pkt.dts = 0;

        //     pkt.duration = (int) av_rescale_q ((int64_t)pkt.duration, inStream->time_base, outStream->time_base);
        //     pkt.pos = -1;

            
        //     std::cout << ""<<std::endl;

        //     if (av_interleaved_write_frame (output.fmtContext, &pkt) < 0)
        //     {
        //         std::cout << "Error occurred when writing packet"<<std::endl;
        //         break;

        //     }
        //     av_free_packet(&pkt);
        // }

        // free (dtsStartFrom);
        // free (ptsStartFrom);
    
        release();
    }
    

    
    // AVOutputFormat* fmt = nullptr;
    // avformat_alloc_output_context2 (&fmt, NULL, NULL, (path+"fdvcx").c_str());


    // for (unsigned int i=0; i<fmt_ctx->nb_streams; i++){
    //     AVStream* in_stream = fmt_ctx->streams[i];
    //     AVCodecContext* in_codec_ctx = in_stream->codec;

    //     AVStream* out_stream = avformat_new_stream (fmt, in_codec_ctx->codec);
        
    //     AVCodecContext* outCodecContext = out_stream->codec;
    // }

    // const unsigned char optionSize = 5;
    // const std::string option[optionSize] = {"-ss", "-to", "-i",  "-c copy", "-y"};
    // mkdir((path+folderName).c_str(),0777);
    // for (int i=0; i<pbfList.size(); i++){
    //     // STime* pTime = parsePbf(path+pbfList[i]);
    //     STime* pTime= parsePbf(path, pbfList[i]);
    //     std::cout<<pTime->hour<<"시"<<pTime->minute<<"분"<<pTime->second<<"초"<<std::endl;
    //     int j =0;
    //     while (pTime[j].value == true){
    //         j++;
    //     }
    //     if (j%2 != 0){
    //         std::cout <<"Chapters are not even number"<<std::endl;
    //         return false;
    //     }
    //     else {
            
    //         for (int k = 0; k<j; k++){
    //             command = "/usr/bin/ffmpeg ";
    //             for (int l=0; l<optionSize; l++){
    //                 switch (l){
    //                     case 0: // -ss
    //                         command += option[l] + " ";
    //                         command += std::to_string(pTime[k].hour)+":";
    //                         command += std::to_string(pTime[k].minute)+":";
    //                         command += std::to_string(pTime[k].second);
    //                         command += " ";
    //                         break;
    //                     case 1: // -to
    //                         k++;
    //                         command += option[l] + " ";
    //                         command += std::to_string(pTime[k].hour)+":";
    //                         command += std::to_string(pTime[k].minute)+":";
    //                         command += std::to_string(pTime[k].second);
    //                         command += " ";
    //                         break;
    //                     case 2: // -i
    //                         command += option[l] + " ";
    //                         command += "\""+path + fileList[i]+"\"";
    //                         command += " ";
    //                         break;
                        
    //                     case 3: // -c copy
    //                         command += option[l] + " ";
    //                         command += "\""+path + folderName;
    //                         command += "/"+pTime[k-1].name+".mp4\"";
    //                         command += " ";
    //                         break;
    //                     case 4: // -y
    //                         command += option[l];
    //                  }
    //             }
    //             system (command.c_str());
    //             //system (("cd "+path+" && "+command).data());
    //         }
    //     }
        
        
    // }
    return true;
}