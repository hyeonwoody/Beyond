BASEDIR=$(dirname $0)
path=${BASEDIR}

mkdir -p /usr/local/include

cp -r ${path}/libs/FFmpeg/libavcodec /usr/local/include
cp -r ${path}/libs/FFmpeg/libavdevice /usr/local/include
cp -r ${path}/libs/FFmpeg/libavfilter /usr/local/include
cp -r ${path}/libs/FFmpeg/libavformat /usr/local/include
cp -r ${path}/libs/FFmpeg/libavutil /usr/local/include
cp -r ${path}/libs/FFmpeg/libswresample /usr/local/include
cp -r ${path}/libs/FFmpeg/libswscale /usr/local/include

mkdir ${path}/build

cd ${path}/build

cmake ..

make

echo "Build Completed!"