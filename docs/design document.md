# Fragile Package Monitor Design Document

v0.1.0

This is the design document describing the applications for the fragile package
monitor, as well as what will be developed and how the software will be structured.

## Use Cases

### How will this be used?

The fragile package montior will be a device with it's own enclosure to be placed
 inside a package that will track, record and send data from the package. This
 will allow someone with the device to get an accurate reading on what condition
 their package is in and will be able to know if their package will be damaged
 in transit.

### What does the package monitor?

The package uses the mangOH red's own internal sensors to monitor temperature,
humidity, shock/acceleration as well as gps location data.

### What triggers communication/alarms with users?

The package will be configured on a trip by trip basis by users which will allow
them to specify what conditions that need to trigger an alarm. Alarms will be configurable,
as well as being able to delivered in multiple ways.

### How is the owner going to be notified?

Ideally, the owner would be notified by a web interface that would also allow
them to monitor the current up-to-date information from the package.
Additionally, configurable alarms should include text(SMS) as well as email notifications.

## Mechanical Details

tbd

## Power

### How long will the battery last on a single charge?

The one major requirement for battery lasting is that it must last for the
duration of a single trip. There are many considerations when it comes to this,
and we will need to determine a much more engineered solution to this problem.
Additionally, there will be a lot of software problems to solve regarding when
to power on hardware sensors as well as when to send data to Airvantage to optimze
power consumption.

## Software Design

### Software Structure

The software will be comprised of 3(?) legato components, each serving an individual
purpose within the software. The first component will be completely focused on
data collection and logging. The second will be focused completely around the
alert component of the software, and will handle detecting as well as notifying
users by means besides Airvantage(SMS, email). The final component will be focused
on sending messages and data to Airvantage, and will also include a lot of logic
surrounding when to send messages and when to sleep the power hungry cellular modem.

### Data Collection Component

The software will be collecting data from sensors at regular intervals(intervals
to be determined at a later date depending on power concerns) and will then
record and log this data to internal storage. This data will follow the following
format(This is subject to change):

``` bash
$TIMESTAMP - $SENSOR: $VALUE

$TIMESTAMP = YYYY:MM:DD:HH:MM:SS
$SENSOR = Temperature/Humidity etc.
$VALUE = 20°C/Latitude/longtitude coordinates.
```

Data will be stored in a UTF-8 encoded text file which will be regularily updated
by the logging component.

### 