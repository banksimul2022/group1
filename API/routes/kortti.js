const express = require('express');
const router = express.Router();
const kortti = require('../models/kortti_model');
const bcrypt = require('bcryptjs');


const saltRounds = 10; //annetaa vähä suolaa sille


router.post('/kortteja', function (request, response) { 

    console.log(request.body.Korttinumero, request.body.PIN); //print stuff
    console.log(request.body);

    if (request.body.Korttinumero) {
        if (request.body.PIN == undefined) { return response.json({ success: false, message: "no pin provided" }) };
        kortti.CheckifCardExists(request.body.Korttinumero, function (err, dbresult) {
            if (err) { return response.json({ success: false, message: "db error" }) }

            if (dbresult == false) {
                return response.json({ success: false, message: 'card doesnt exist' });
            }

            else {
                kortti.getPIN(request.body.Korttinumero, function (err, dbResult) {
                    if (err) {
                        return response.json({ success: false, message: "db error" }); //palautetaan virhe koska tietokanta on tulessa
                    }
                    else {
                        console.log("request  " + request.body.PIN)
                        console.log("database " + dbResult[0].PIN)

                        bcrypt.compare(request.body.PIN, dbResult[0].PIN, function (err, res) { //async compare 
                            if (err) { //error handler

                                return response.json({ success: false, message: 'error while comparing values' });
                            }
                            if (res) {
                                return response.json({ pin: true });
                            }

                            else {
                                return response.json({ pin: false });
                            }
                        });
                    }
                });
            }
        })
    }
    else {
        return response.json("error")
    }

});



router.post('/', function (request, response) {
    kortti.addCard(request.body, function (err, count) {
        if (err) {
            response.json(err);
        } else {
            response.json(request.body);
        }

    });
});


module.exports = router;