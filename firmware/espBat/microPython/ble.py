from machine import Pin
from time import sleep_ms
import ubluetooth

ble = ubluetooth.BLE()
ble.active(True)

ble.gap_advertise(100, adv_data = b'\x02\x01\x06\x03\x09\x41\x42')