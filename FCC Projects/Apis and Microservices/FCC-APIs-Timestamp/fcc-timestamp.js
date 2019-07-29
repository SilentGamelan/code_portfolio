const express = require('express');
const router = express.Router();


router.get('/', function(req, res, next) {
    res.send('Validate your timestamp at /api/timestamp/[yourTimestamp]');
    next();
});

router.get('/api/timestamp/:userTime', function(req, res, next) {
    let userTime = req.params.userTime;
    
    if(userTime == null && userTime == "") {
        next(res.send(userTime = new Date()));
    }

    userTime = new Date(userTime);

    if(userTime === NaN) {
        next(res.send({"error": "Invalid Date"}));
    } else {
        next(res.send({
            "unix"  : userTime.getTime(),
            "utc"   : userTime.toUTCString()
        }));
    }

});


module.exports = router;