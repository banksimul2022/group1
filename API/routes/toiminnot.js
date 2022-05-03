const express = require('express');
const router = express.Router();
const toiminnot = require('../models/toiminnot_model');

//function for checking balance
router.post('/balance', function (request, response) {

    if (request.body.Korttinumero) {

        toiminnot.checkBalance(request.body.Korttinumero, function (err, dbResult) {
            if (err) {
                return response.json({ success: false });
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

//function for checking card holder data
router.post('/card_data', function (request, response) {

    if (request.body.Korttinumero) {

        toiminnot.getInfo(request.body.Korttinumero, function (err, dbResult) {
            if (err) {
                return response.json({ success: false });
            } else {
                console.log(dbResult);
                return response.json({ success: true, dbResult });
            }
        });
    }

    else {
        return response.json("error")
    }

});

//simple withdrawal function w/out tilitapahtumat
router.post('/nosto/simple', function (request, response) {

    if (request.body.Korttinumero) {
        if (request.body.rahasumma == undefined) { return response.json({ success: false, message: "no withdrawal amount given" }) };
        console.log("nosto/simple body: ");
        console.log(request.body);
        toiminnot.checkBalance(request.body.Korttinumero, function (err, dbResult) {
            if (err) {
                return response.json({ success: false, message: "db error" })
            } else {
                console.log(dbResult[0].Saldo);
                if (dbResult[0].Saldo >= request.body.rahasumma) {

                    toiminnot.getTiliID(request.body.Korttinumero, function (err, dbResult) {
                        if (err) {
                            return response.json({ success: false, message: "db error" })
                        }
                        else {
                            console.log("tultiin ulos getTiliID funktiosta TiliID on: ");
                            TiliID = dbResult[0].Tili_idTili;
                            console.log(TiliID);

                            toiminnot.SimpleWithdrawal(request.body.rahasumma, TiliID, function (err, dbResult) {
                                if (err) {
                                    console.log("db error");
                                    return response.json({ success: false, message: "withdrawal error" })
                                }
                                else {
                                    console.log("withdrawal success");
                                    return response.json({ success: true, message: dbResult })
                                }
                            });
                        }
                    });
                }
                else {
                    console.log("rahat ei riittäny");
                    return response.json({ success: false, message: "Insufficient funds" });
                }
            }
        });
    }

    else {
        return response.json({ success: false, message: "undefined" })
    }

});

//ei käytössä (kesken) ->
router.post('/nosto', function (request, response) {

    if (request.body.Korttinumero) {
        if (request.body.rahasumma == undefined) { return response.json({ success: false, message: "no withdrawal amount given" }) };

        toiminnot.checkBalance(request.body.Korttinumero, function (err, dbResult) {
            if (err) {
                return response.json({ success: false, message: "db error" })
            } else {
                console.log(dbResult);
                if (dbResult[0].Saldo >= request.body.rahasumma) {
                    console.log(dbResult[0].Saldo);

                    toiminnot.Withdrawal(request.body.Korttinumero, request.body.rahasumma, function (err, result) {
                        if (err) {
                            return response.json({ success: false, message: "withdrawal error" })
                        }
                        else {
                            return response.json({ success: true, message: result })
                        }

                    });

                }
                else {
                    return response.json({ success: false, message: "Insufficient funds" });
                }


            }
        });
    }

    else {
        return response.json({ success: false, message: "error" })
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