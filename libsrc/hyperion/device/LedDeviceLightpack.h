#pragma once

// stl includes
#include <vector>
#include <cstdint>
#include <string>

// libusb include
#include <libusb.h>

// Hyperion includes
#include <hyperion/LedDevice.h>

///
/// LedDevice implementation for a lightpack device (http://code.google.com/p/light-pack/)
///
class LedDeviceLightpack : public LedDevice
{
public:
	///
	/// Constructs the LedDeviceLightpack
	///
	LedDeviceLightpack();

	///
	/// Destructor of the LedDevice; closes the output device if it is open
	///
	virtual ~LedDeviceLightpack();

	///
	/// Opens and configures the output device
	///
	/// @return Zero on succes else negative
	///
	int open(const std::string & serialNumber = "");

	///
	/// Writes the RGB-Color values to the leds.
	///
	/// @param[in] ledValues  The RGB-color per led
	///
	/// @return Zero on success else negative
	///
	virtual int write(const std::vector<ColorRgb>& ledValues);

	///
	/// Writes the RGB-Color values to the leds.
	///
	/// @param[in] ledValues  Array of RGB values
	/// @param[in] size       The number of RGB values
	///
	/// @return Zero on success else negative
	///
	int write(const ColorRgb * ledValues, int size);

	///
	/// Switch the leds off
	///
	/// @return Zero on success else negative
	///
	virtual int switchOff();

	/// Get the serial of the Lightpack
	const std::string & getSerialNumber() const;

	/// Get the number of leds
	int getLedCount() const;

private:
	///
	/// Test if the device is a (or the) lightpack we are looking for
	///
	/// @return Zero on succes else negative
	///
	int testAndOpen(libusb_device * device, const std::string & requestedSerialNumber);

	/// write bytes to the device
	int writeBytes(uint8_t *data, int size);

	/// Disable the internal smoothing on the Lightpack device
	int disableSmoothing();

	struct Version
	{
		int majorVersion;
		int minorVersion;
	};

	static libusb_device_handle * openDevice(libusb_device * device);
	static std::string getString(libusb_device * device, int stringDescriptorIndex);

private:
	/// libusb context
	libusb_context * _libusbContext;

	/// libusb device handle
	libusb_device_handle * _deviceHandle;

	/// harware bus number
	int _busNumber;

	/// hardware address number
	int  _addressNumber;

	/// device serial number
	std::string _serialNumber;

	/// firmware version of the device
	Version _firmwareVersion;

	/// the number of leds of the device
	int _ledCount;

	/// the number of bits per channel
	int _bitsPerChannel;

	/// buffer for led data
	std::vector<uint8_t> _ledBuffer;
};
