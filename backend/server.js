const express = require('express');
const sensorRoutes = require('./routes/sensors');
const app = express();
const PORT = process.env.PORT || 3000;

// Middleware
app.use(express.json());

// Routes
app.use('/sensors', sensorRoutes);

app.listen(PORT, () => {
    console.log(`Server is running on port ${PORT}`);
});
