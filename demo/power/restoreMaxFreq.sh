for x in /sys/devices/system/cpu/*/cpufreq/; do echo 4600000 | sudo tee $x/scaling_max_freq; done
