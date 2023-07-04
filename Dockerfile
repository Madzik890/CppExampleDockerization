FROM ubuntu:20.04

WORKDIR /webservice

ENV DEBIAN_FRONTEND=noninteractive 
ENV TZ=Europe/Berlin
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

RUN apt-get update
#-y is for accepting yes when the system asked us for installing the package
RUN apt-get install -y build-essential gcc g++ cmake gdb pkg-config valgrind systemd-coredump

COPY app app

EXPOSE 8088/tcp

#building 
RUN mkdir /webservice/app/build 
RUN cd /webservice/app/build && cmake .. && make -j4

#CMD ["/webservice/app/build/WebService"]
ENTRYPOINT ["/webservice/app/build/WebService"]

