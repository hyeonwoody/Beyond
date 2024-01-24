
#include "VideoCut.h"

#include <iostream>
#include <fstream>
#include <codecvt>
#include <locale>
#include <string>
#include <cstdlib>


#define LOG_VIDEOCUT 0

extern "C" {

    #include <libavutil/timestamp.h>
    #include <libavformat/avformat.h>
}

#include <sys/stat.h> // mkdir


struct SFile {
    AVFormatContext *formatContext;
    std::string fileName;
};

static void logPacket (const AVFormatContext *fmtContext, const AVPacket *pkt, const char *tag){
    AVRational *timeBase = &fmtContext->streams[pkt->stream_index]->time_base;

    printf("%s: pts:%s  dts:%s  duration:%s stream_index:%d\n",
           tag,
           std::to_string (pkt->pts).c_str(),
           std::to_string(pkt->dts).c_str(),
           std::to_string(pkt->duration).c_str(),
           pkt->stream_index);
}


std::string utf16_to_utf8(std::u16string const& str){
    std::wstring_convert<std::codecvt_utf8_utf16<char16_t, 0x10ffff, std::codecvt_mode::little_endian>, char16_t> cnv;
    std::string utf8 = cnv.to_bytes(str);
    if (cnv.converted() < str.size()){

    }
    return utf8;
}

CVideoCut::STime* CVideoCut::parsePbf(std::string path, std::string file){

    std::ifstream openFile(path+file);
    int numLine = 0;
    std::vector<std::string> number = {};
    std::vector<std::string> name = {};
    std::string line;
    std::string tmp;

    CVideoCut::STime* pTime;

    openFile.seekg(0, std::ios::end);
    size_t size = (size_t) openFile.tellg();

    //skip Bom
    openFile.seekg(2, std::ios::beg);
    size -= 2;

    std::u16string u16((size / 2) + 1, '\0');
    openFile.read((char*)&u16[0], size);
    std::string what = utf16_to_utf8(u16);


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
    pTime = (CVideoCut::STime*)malloc(sizeof(CVideoCut::STime)*numLine);
    memset(pTime, 0, sizeof(CVideoCut::STime)*numLine);
    for (int i=0; i<numLine; i++){
        pTime[i].second = (stoi(number[i]) / 1000) % 60;
        pTime[i].minute = (stoi(number[i]) / 1000) / 60;
        while (pTime[i].minute >= 60){
            pTime[i].minute -= 60;
            pTime[i].hour = +1;
        }
        pTime[i].source = file;
        pTime[i].name = name[i];
        pTime[i].value = true;
    }
    return pTime;
}


int CVideoCut::proceed (CJob* pJob, SOptionGroup* optionGroup, SFlagGroup* flagGroup){
    
    std::string path = optionGroup->workPath + "/";
    std::string folderName = "Clips";
    std::string currentTag = optionGroup->fileTag;
    int nbClips = 0;

    std::vector <std::string> pbfList;
    std::vector <std::string> fileList;

    CJob::CSubJob* pSubJob = pJob->pSubJob;
    std::string command = "";

    pSubJob->getDirectory(path);
    pbfList = pSubJob->pbfList;
    fileList = pSubJob->fileList;

    AVPacket* pkt;
    
    AVOutputFormat *outputFormat = NULL;
    

    int ret = 0;

    int streamMappingSize = 0;
    int *streamMapping = NULL;
    int streamIndex = 0;

    CVideoCut::STime* pTime = NULL;
    std::cout<<av_version_info()<<std::endl;
    for (int i=0; i<pbfList.size(); i++){
        pTime= parsePbf(path, pbfList[i]);
        int j=0;
        while (pTime[j].value == true){
            j++;
        }
        nbClips = j/2;
        if (j%2 != 0){
            std::cout <<"Chapters are not even number"<<std::endl;
            return -1;
        }

        for (int k=0; k < nbClips*2; k+=2){
            CVideoCut::SClip* tmpClip = new SClip();
            //tmpVideo->source = pTime[j].source.substr(0, pTime.size()-4);
            for (int l=0; l<fileList.size(); l++){
                if (fileList[l].substr(0, fileList[l].size() - 3) == pTime[k].source.substr(0, pTime[k].source.size() - 3)){
                    tmpClip->source = fileList[l];
                    break;
                }
            }
            tmpClip->name = pTime[k].name;
            tmpClip->startTime = pTime[k].hour * 3600 + pTime[k].minute * 60 + pTime[k].second;
            tmpClip->endTime = pTime[k+1].hour * 3600 +  pTime[k+1].minute * 60 + pTime[k+1].second;
            clipList.push_back(tmpClip);
        }
    }

    free(pTime);

    mkdir ((path + folderName).c_str(), 0777);

    for (int i=0; i<clipList.size(); i++){

        SFile input = {NULL, ""};
        SFile output = {NULL, ""};
        input.fileName = path + clipList[i]->source;
        if ((ret = avformat_open_input(&input.formatContext, input.fileName.c_str(), NULL, NULL)) < 0){
            std::cout<<"Could not open source file : "<<input.fileName<<std::endl;
        }
        output.fileName = (path + folderName) + "/" + clipList[i]->name+".mp4";
        if ((ret = avformat_find_stream_info(input.formatContext, 0)) < 0){
            std::cout<<"Could not find stream information"<<std::endl;
        }
    
        //dump input information to stderr
        av_dump_format (input.formatContext, 0, input.fileName.c_str(), 0);

        avformat_alloc_output_context2(&output.formatContext, NULL, NULL, output.fileName.c_str());
        if (!output.formatContext){
            std::cout<<"Could not create output context"<<std::endl;
            ret = AVERROR_UNKNOWN;
        }

        streamMappingSize = input.formatContext->nb_streams;
        streamMapping = (int *) av_malloc_array (streamMappingSize, sizeof(*streamMapping));
        if (!streamMapping){
            ret = AVERROR (ENOMEM);
        }
        int startTime = clipList[i]->startTime;
        int endTime =clipList[i]->endTime;

        int *startSeconds = (int *) malloc (streamMappingSize * sizeof(int));
        int *endSeconds = (int *) malloc (streamMappingSize * sizeof(int));

        outputFormat = output.formatContext->oformat;

        // copy streams from the input file to the output file
        /**
         * Segmentation fault on av_packet_rescale_ts if streamIndex is not initialzed
        */
        streamIndex = 0;
        for (int index = 0; index < streamMappingSize; index++){
            AVStream *outStream;
            AVStream *inStream = input.formatContext->streams[index];
            AVCodecParameters *inCodecPar = inStream->codecpar;

            startSeconds[index] = av_rescale_q (startTime * AV_TIME_BASE, AV_TIME_BASE_Q, inStream->time_base);
            endSeconds[index] = av_rescale_q (endTime * AV_TIME_BASE, AV_TIME_BASE_Q, inStream->time_base);

            if (inCodecPar->codec_type != AVMEDIA_TYPE_VIDEO &&
                inCodecPar->codec_type != AVMEDIA_TYPE_AUDIO &&
                inCodecPar->codec_type != AVMEDIA_TYPE_SUBTITLE){
                    streamMapping[index] = -1;
                    continue;
                }
            streamMapping [index] = streamIndex++;

            outStream = avformat_new_stream (output.formatContext, NULL);
            if (!outStream){
                std::cout<<"Failed allocating output stream"<<std::endl;
                ret = AVERROR_UNKNOWN;
            }

            ret = avcodec_parameters_copy (outStream->codecpar, inCodecPar);
            if (ret < 0){
                std::cout << "Failed to copy coec parameter" << std::endl;
            }


            outStream->codecpar->codec_tag = 0;
        }

        av_dump_format (output.formatContext, 0, output.fileName.c_str(), 1);
        
        if (!(outputFormat->flags & AVFMT_NOFILE)){
            ret = avio_open (&output.formatContext->pb, output.fileName.c_str(), AVIO_FLAG_WRITE);
            if (ret < 0){
                std::cout << "Could not open output file"<<std::endl;
            }
        }

        ret = avformat_write_header (output.formatContext, NULL);
        if (ret < 0){
            std::cout << "Error occujred when opening output file"<<std::endl;
        }

        ret = avformat_seek_file (input.formatContext, -1, INT64_MIN,startTime*AV_TIME_BASE, startTime*AV_TIME_BASE, 0);
        if (ret < 0){
            std::cout<<"Failed to seek the input file"<<std::endl;
        }

        
        pkt = av_packet_alloc ();
        if (!pkt){
            std::cout << "Failed to allocate packet"<<std::endl;
        }
        while (1){
            AVStream *inStream;
            AVStream *outStream;
            ret = av_read_frame (input.formatContext, pkt);
            if (ret < 0)
                break;

            if (pkt->stream_index >= streamMappingSize || streamMapping[pkt->stream_index] < 0 
                //||
                ||pkt->pts > endSeconds[pkt->stream_index]
                ){
                av_packet_unref (pkt);
                continue;
            }
            inStream = input.formatContext->streams[pkt->stream_index];

            pkt->stream_index = streamMapping[pkt->stream_index];
            outStream = output.formatContext->streams[pkt->stream_index];
            #if LOG_VIDEOCUT
            logPacket (input.formatContext, pkt, "in");
            #endif

            //copy packet
            // pkt->pts = av_rescale_q_rnd (pkt->pts, inStream->time_base, outStream->time_base, static_cast<AVRounding> (AV_ROUND_NEAR_INF|AV_ROUND_PASS_MINMAX));
            // pkt->dts = av_rescale_q_rnd (pkt->dts, inStream->time_base, outStream->time_base, static_cast<AVRounding>(AV_ROUND_NEAR_INF|AV_ROUND_PASS_MINMAX));
            // pkt->duration = av_rescale_q (pkt->duration, inStream->time_base, outStream->time_base);
            // pkt->pos = -1;
            // logPacket (output.formatContext, &pkt, "out");

            //shift the packet
            pkt->pts -= startSeconds[pkt->stream_index];
            pkt->dts -= startSeconds[pkt->stream_index];
            #if LOG_VIDEOCUT
            logPacket (output.formatContext, pkt, "out");
            #endif
            av_packet_rescale_ts (pkt, input.formatContext->streams[pkt->stream_index]->time_base, 
                                    output.formatContext->streams[pkt->stream_index]->time_base);
            pkt->pos = -1;
            #if LOG_VIDEOCUT
            logPacket (output.formatContext, pkt, "out");
            #endif
            ret = av_interleaved_write_frame (output.formatContext, pkt);
            if (ret <0){
                std::cout<<"Error muxing packet"<<std::endl;
                break;
            }
            av_packet_unref(pkt);
        }
        av_write_trailer (output.formatContext);

        //close
        
        av_packet_free(&pkt);
        avformat_close_input (&input.formatContext);
        if (output.formatContext && !(outputFormat->flags & AVFMT_NOFILE))
            avio_closep (&output.formatContext->pb);
        avformat_free_context (output.formatContext);

        av_freep (&streamMapping);
        free(startSeconds);
        free(endSeconds);
        if (ret < 0 && ret!= AVERROR_EOF){
            std::cout<< "Error occured : "<<std::endl;
            this->setResult(-1);
        }
        
    }
    int a =0;
    return 0;
}