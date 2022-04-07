const express = require('express');
const router = express.Router();
const toiminnot = require('../models/toiminnot_model');

router.get('/:Korttinumero?/:rahasumma?', function (request, response) {

    if (request.params.Korttinumero) {
        if (request.params.rahasumma == undefined) { return response.json({ success: false, message: "no summa provided" }) };

        toiminnot.checkBalance(request.params.Korttinumero, function (err, dbResult) {
            if (err) {
                response.json(err);
            } else {
                console.log(dbResult);
                if (dbResult[0].Saldo >= request.params.rahasumma) {

                    toiminnot.getInfo(request.params.Korttinumero, function (err, data) {
                        console.log(data);
                        console.log(dbResult[0].Saldo);
                        return response.json("rahat riittää");
                    });

                }
                else {
                    return response.json({success: false, message: "Insufficient funds"});
                }
                //response.json(dbResult);

                //if (rahasumma)
            }
        });
    }

    else {
        return response.json("yritäkkö rikkoo mun serveriä tyhjillä requesteillä hä?????")
    }

});

router.get('nosto/:Korttinumero?/:rahasumma?', function (request, response) {

    if (request.params.Korttinumero) {
        if (request.params.rahasumma == undefined) { return response.json({ success: false, message: "no summa provided" }) };

        toiminnot.checkBalance(request.params.Korttinumero, function (err, dbResult) {
            if (err) {
                response.json(err);
            } else {
                console.log(dbResult);
                if (dbResult[0].Saldo >= request.params.rahasumma) {
                    console.log(dbResult[0].Saldo);

                    toiminnot.Withdrawal(request.params.Korttinumero, request.params.rahasumma, function (err, result) {

                    })

                }
                else {
                    return response.json({success: false, message: "Insufficient funds"});
                }



                //response.json(dbResult);

                //if (rahasumma)
            }
        });
    }

    else {
        return response.json("yritäkkö rikkoo mun serveriä tyhjillä requesteillä hä?????")
    }

});

router.post('/',
    function (request, response) {
        toiminnot.add(request.body, function (err, count) {
            if (err) {
                response.json(err);
            } else {
                response.json(request.body);
            }
        });
    });





module.exports = router;