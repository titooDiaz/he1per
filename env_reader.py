import os
from dotenv import load_dotenv

load_dotenv(".env")

def before_build(source, target, env):
    ssid = os.getenv("WIFI_SSID")
    passwd = os.getenv("WIFI_PASS")

    if ssid:
        env.Append(CCFLAGS=[f'-DWIFI_SSID="{ssid}"'])
    if passwd:
        env.Append(CCFLAGS=[f'-DWIFI_PASS="{passwd}"'])
