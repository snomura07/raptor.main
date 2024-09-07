
# baseはbase_build/armv6内に記載
FROM snomura07/raptor_armv6_base_img:latest

# add sudo user
RUN groupadd -g 1000 developer && \
    useradd  -g      developer -G sudo -m -s /bin/bash pi && \
    echo 'pi:pi' | chpasswd
RUN echo 'Defaults visiblepw'        >> /etc/sudoers
RUN echo 'pi ALL=(ALL) NOPASSWD:ALL' >> /etc/sudoers

USER pi
WORKDIR /home/pi

# Add LD_LIBRARY_PATH to point to the cross-compiled libraries
ENV LD_LIBRARY_PATH=/usr/local/lib:$LD_LIBRARY_PATH

# setting alias
RUN echo "alias ll='ls -l'" >> ~/.bashrc
