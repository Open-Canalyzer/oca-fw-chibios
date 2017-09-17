#ifndef USB_COMMUNICATION_H
#define USB_COMMUNICATION_H

#include <stdint.h>

typedef struct oca_usb_data_frame oca_usb_data_frame;
struct oca_usb_data_frame
{
  char data[128];	//TBD: Depends on the max protobuf frame size
  uint8_t dataSize;
};

void oca_usb_init(void);



#endif /* USB_COMMUNICATION_H */