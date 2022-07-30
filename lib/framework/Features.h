#ifndef Features_h
#define Features_h

#define FT_ENABLED(feature) feature

// project feature off by default
#ifndef FT_PROJECT
#define FT_PROJECT 0
#endif

// security feature on by default
#ifndef FT_SECURITY
#ifdef LINUX
#define FT_SECURITY 1
#else
#define FT_SECURITY 1
#endif
#endif

// mqtt feature on by default
#ifndef FT_MQTT
#ifdef LINUX
#define FT_MQTT 0
#else
#define FT_MQTT 1
#endif
#endif

// ntp feature on by default
#ifndef FT_NTP
#ifdef LINUX
#define FT_NTP 0
#else
#define FT_NTP 1
#endif
#endif

// mqtt feature on by default
#ifndef FT_OTA
#ifdef LINUX
#define FT_OTA 0
#else
#define FT_OTA 1
#endif
#endif

// upload firmware feature off by default
#ifndef FT_UPLOAD_FIRMWARE
#define FT_UPLOAD_FIRMWARE 0
#endif


#endif
