FROM ubuntu:20.04 AS build

ENV DEBIAN_FRONTEND=noninteractive
ENV TZ=America/New_York

RUN apt-get update && \
    apt-get install -y tzdata build-essential cmake libcurl4-openssl-dev libcpprest-dev libssl-dev git && \
    ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

WORKDIR /app
COPY . /app

RUN rm -rf build && mkdir build && cd build && cmake .. && make

FROM ubuntu:20.04

ENV DEBIAN_FRONTEND=noninteractive
ENV TZ=America/New_York

RUN apt-get update && \
    apt-get install -y tzdata build-essential cmake libcurl4-openssl-dev libcpprest-dev libssl-dev && \
    ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

WORKDIR /app
COPY --from=build /app/build/SportPulse /app/SportPulse

EXPOSE 8080

CMD ["./SportPulse", "--api"]
