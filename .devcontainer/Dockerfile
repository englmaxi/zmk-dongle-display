FROM docker.io/zmkfirmware/zmk-dev-arm:4.1-branch

ARG ZMK_URL
ARG ZMK_BRANCH
ARG ZMK_PATH

# clone zmk
RUN git clone --filter=tree:0 --single-branch --branch=${ZMK_BRANCH} ${ZMK_URL} ${ZMK_PATH}

# copy .bashrc with build functions
COPY build-zmk.sh /usr/local/bin/build-zmk
COPY build-rommana.sh /usr/local/bin/build-rommana
COPY build-sweep.sh /usr/local/bin/build-sweep

RUN chmod +x /usr/local/bin/build-zmk /usr/local/bin/build-rommana /usr/local/bin/build-sweep
