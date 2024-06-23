
# baseはbase_bild/x86_64内に記載
FROM snomura07/raptor_x86_64_build_img

# add sudo user
RUN groupadd -g 1000 developer && \
    useradd  -g      developer -G sudo -m -s /bin/bash nomura && \
    echo 'nomura:robo2006' | chpasswd
RUN echo 'Defaults visiblepw'             >> /etc/sudoers
RUN echo 'nomura ALL=(ALL) NOPASSWD:ALL' >> /etc/sudoers

USER nomura
WORKDIR /home/nomura

# Add LD_LIBRARY_PATH to point to the cross-compiled libraries
ENV LD_LIBRARY_PATH=/home/nomura/lib:$LD_LIBRARY_PATH
ENV LD_LIBRARY_PATH=/usr/arm-linux-gnueabi/lib:$LD_LIBRARY_PATH
RUN echo 'exec(){ qemu-arm -L /usr/arm-linux-gnueabi $@; }' >> .bashrc
