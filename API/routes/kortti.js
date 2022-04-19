const express = require('express');
const router = express.Router();
const kortti = require('../models/kortti_model');
const bcrypt = require('bcryptjs');

const saltRounds = 10; //annetaa vähä suolaa sille

router.get('/:Korttinumero?/:PIN?', function (request, response) { //kannattaa sitte lähettää pin koodis http liikenteessä

    console.log(request.params.Korttinumero, request.params.PIN); //print stuff

    if (request.params.Korttinumero) {
        if (request.params.PIN == undefined) { return response.json({ success: false, message: "no pin provided" }) };
        kortti.CheckifCardExists(request.params.Korttinumero, function (err, dbresult) {
            if (err) { return response.json({ success: false, message: "db error" }) }

            if (dbresult == false) {
                return response.json({ success: false, message: 'card doesnt exist' });
            }

            else {
                kortti.getPIN(request.params.Korttinumero, function (err, dbResult) {
                    if (err) {
                        return response.json({ success: false, message: "db error" }); //palautetaan virhe koska tietokanta on tulessa
                    }
                    else {
                        console.log("request  " + request.params.PIN)
                        console.log("database " + dbResult[0].PIN)

                        bcrypt.compare(request.params.PIN, dbResult[0].PIN, function (err, res) { //async compare 
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
        return response.json("yritäkkö rikkoo mun serveriä tyhjillä requesteillä hä?????")
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