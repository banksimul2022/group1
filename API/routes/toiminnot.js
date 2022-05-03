const express = require('express');
const router = express.Router();
const toiminnot = require('../models/toiminnot_model');


router.post('/money', function (request, response) {

    if (request.body.Korttinumero) {
        if (request.body.rahasumma == undefined) { return response.json({ success: false, message: "no summa provided" }) };
        //check if card exists

        toiminnot.checkBalance(request.body.Korttinumero, function (err, dbResult) {
            if (err) {
                response.json(err);
            } else {
                console.log(dbResult);
                if (dbResult[0].Saldo >= request.body.rahasumma) {

                    toiminnot.getInfo(request.body.Korttinumero, function (err, data) {
                        console.log(data);
                        console.log(dbResult[0].Saldo);
                        return response.json({ success: true, message: "rahat riittää" });
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

//function for checking balance
router.post('/balance', function (request, response) {

    if (request.body.Korttinumero) {
        
        toiminnot.checkBalance(request.body.Korttinumero, function (err, dbResult) {
            if (err) {
                return response.json({ success: false});
            } else {
                console.log(dbResult);
                return response.json({ success: true, balance: dbResult[0].Saldo });
            }
        });
    }

    else {
        return response.json("error")
    }

});

router.post('/card_data', function (request, response) {

    if (request.body.Korttinumero) {
        
        toiminnot.getInfo(request.body.Korttinumero, function (err, dbResult) {
            if (err) {
                return response.json({ success: false});
            } else {
                console.log(dbResult);
                return response.json({ success: true, dbResult});
            }
        });
    }

    else {
        return response.json("error")
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