for x in /sys/devices/system/cpu/*/cpufreq/; do echo 800000 | sudo tee $x/scaling_max_freq; done

#sudo echo "800000" > /sys/devices/system/cpu/cpu0/cpufreq/cpuinfo_max_freq
