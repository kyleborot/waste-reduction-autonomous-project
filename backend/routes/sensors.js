const express = require('express');
const router = express.Router();
const { getSensorData } = require('../arduino');

// Endpoint to get sensor data
router.get('/data', async (req, res) => {
    try {
        const data = await getSensorData();
        res.json({ data });
    } catch (error) {
        res.status(500).json({ error: 'Failed to get sensor data' });
    }
});

module.exports = router;
