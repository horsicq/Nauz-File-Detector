#####################################################
# BUILD ARG when using with:
#   docker build . --build-arg arg1=val1
#
#  image: the base docker image to be used. defaults
#         to ubuntu:bionic
#  environment: defines if the build-host has access
#               to internet or not (darksite).
#               when building for darksite, you need
#               to have a Nauz-File-Detector.tar.gz
#               inside the build directory.
#               defaults to internet.
#####################################################
ARG image=ubuntu:bionic
ARG environment=internet



#####################################################
# Source stage when building with internet connection
#####################################################
FROM ${image} as source-internet

ARG environment

RUN apt-get update --quiet && \
    apt-get install --quiet --assume-yes git
RUN if [ "x$environment" = "xinternet" ]; then git clone --recursive https://github.com/horsicq/Nauz-File-Detector.git; fi



#####################################################
# Source stage when building inside a darksite
#####################################################
FROM ${image} as source-darksite

#ADD Nauz-File-Detector.tar.g[z] /



#####################################################
# Build stage
#####################################################
FROM source-${environment} as builder

RUN apt-get update --quiet
RUN apt-get install --quiet --assume-yes \
      build-essential \
      qtbase5-dev \
      qtdeclarative5-dev \
      qttools5-dev-tools \
      qt5-default \
      qt5-qmake

RUN qtchooser -print-env \
 && qmake --version

RUN cd Nauz-File-Detector \
 && chmod 755 build_lin64.sh \
 && cd console_source \
 && qmake console_source.pro -spec linux-g++ \
 && make -f Makefile



#####################################################
# Run stage
#####################################################
FROM ${image}

RUN apt-get update --quiet && \
    apt-get install --quiet --assume-yes \
       gosu \
       qt5-default \
    && \
    rm -rf /var/cache/apt/*

COPY --from=builder /Nauz-File-Detector/build/release/nfdc /opt/Nauz-File-Detector/

RUN mkdir -p /sample

WORKDIR /opt/Nauz-File-Detector

ENTRYPOINT ["gosu", "nobody", "/opt/Nauz-File-Detector/nfdc"]

CMD ["--help"]
