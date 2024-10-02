const SerialPort = require('serialport');
const Readline = require('@serialport/parser-readline');

const port = new SerialPort('/dev/ttyUSB0', { baudRate: 9600 }); // Adjust based on your Arduino connection
const parser = port.pipe(new Readline({ delimiter: '\n' }));

let coordinatesArray = [];
// Function to get sensor data from Arduino
const getSensorData = () => {
    return new Promise((resolve, reject) => {
        parser.once('data', (data) => {
            //Data will be in (x, y, z) format
            const [x, y, z] = data.trim().split(',').map(Number);

            coordinatesArray.push({x, y, z});

            resolve({x, y, z});
        });

        port.write('GET_DATA\n', (err) => {
            if (err) {
                reject('Error writing to port: ' + err.message);
            }
        });
    });
};

module.exports = { getSensorData, coordinatesArray };
