FROM ubuntu:22.04

ENV TZ=Asia/Tokyo
RUN apt-get update && apt-get install -y tzdata
RUN dpkg-reconfigure --frontend noninteractive tzdata
RUN apt-get update && apt-get install -y \
    build-essential \
    make \
    gcc \
    libx11-dev \
    libxext-dev \
    libbsd-dev \
    libmlx5-dev \
    && apt-get clean
COPY . /app
WORKDIR /app
RUN cd cub3D && make

# TODO x11対応
# https://qiita.com/nobrin/items/59b9b645e5595365c4ac
# 最後にコマンドを実行するためにコンテナを開く（任意）
CMD ["bash"]
