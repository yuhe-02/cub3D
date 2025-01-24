# ベースイメージとして Ubuntu 22.04 を指定
FROM ubuntu:22.04

# タイムゾーンの設定 (任意)
ENV TZ=Asia/Tokyo
RUN apt-get update && apt-get install -y tzdata
RUN dpkg-reconfigure --frontend noninteractive tzdata

# 基本的なパッケージのインストール
RUN apt-get update && apt-get install -y \
    build-essential \
    make \
    gcc \
    g++ \
    git \
    wget \
    curl \
    libx11-dev \
    libxext-dev \
    libbsd-dev \
    libmlx5-dev \
    && apt-get clean

# リポジトリをコンテナ内の指定ディレクトリにコピー
# 現在のホストディレクトリをコンテナ内の `/app` にコピー
COPY . /app

# 作業ディレクトリをリポジトリ内に設定
WORKDIR /app

# make を実行してプロジェクトをビルド
RUN make

# 最後にコマンドを実行するためにコンテナを開く（任意）
CMD ["bash"]
