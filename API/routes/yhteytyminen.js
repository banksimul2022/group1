const { Router } = require('express');
const express = require('express');
const router = express.Router();
const yhteytyminen = require('../models/yhteytyminen_model');

router.post('/', 
function(request, response) {
  yhteytyminen.add(request.body, function(err, count) {
    console.log(count);
    if (err) {
      response.json(err);
    } else {
      response.json(request.body); 
      
    }
  });
});

module.exports = router;