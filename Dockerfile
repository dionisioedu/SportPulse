FROM ubuntu:20.04

ENV DEBIAN_FRONTEND=noninteractive

RUN echo "tzdata tzdata/Areas select America" | debconf-set-selections && \
    echo "tzdata tzdata/Zones/America select New_York" | debconf-set-selections && \
    apt-get update && apt-get install -y tzdata \
    build-essential \
    cmake \
    libcurl4-openssl-dev \
    git

WORKDIR /app

COPY . /app

RUN rm -rf build && mkdir build && cd build && cmake .. && make

CMD ["./build/SportPulse"]