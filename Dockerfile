FROM ubuntu:20.04

WORKDIR /webservice

ENV DEBIAN_FRONTEND=noninteractive 

RUN apt-get update
RUN apt-get install -y gcc g++ cmake 

COPY app app

EXPOSE 8088/tcp

#building 
RUN mkdir /webservice/app/build 
RUN cd /webservice/app/build && cmake .. && make
RUN mv /webservice/app/build/WebService /webservice/app/ 
RUN rm -r /webservice/app/build

ENTRYPOINT ["/webservice/app/WebService"]

