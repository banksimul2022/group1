const express = require('express');
const router = express.Router();
const kortti = require('../models/kortti_model');
const bcrypt = require('bcryptjs');

const saltRounds = 10;



router.get('/:Korttinumero?/:PIN?', function (request, response) { //kannattaa sitte lähettää pin koodis http liikenteessä

    console.log(request.params.Korttinumero, request.params.PIN); //printataan kortin numero ja pin


    if (request.params.Korttinumero && request.params.PIN) {
        kortti.getByCardNumber(request.params.Korttinumero, function (err, dbResult) {
            if (err) {
                response.json(err); //palautetaan virhe koska tietokanta on tulessa
            }

            else {


                pinni = dbResult[0].PIN;
                const hassi = bcrypt.hash(request.params.PIN, saltRounds).then( //asynkki toimimaa viel
                    bcrypt.compare(hassi, pinni, function (err, res) {
                        if (err) {
                            // handle error
                        }
                        if (res) {
                            return response.json({ success: true, message: 'o' });
                        }
    
                        else {
                            return response.json({ success: false, message: 'f' });
                        }
                    })
                );
                //console.log(pinni);
                //console.log(hassi);

                //response.json(dbResult);
                /*
                bcrypt.compare(hassi, pinni, function (err, res) {
                    if (err) {
                        // handle error
                    }
                    if (res) {
                        return response.json({ success: true, message: 'password ok' });
                    }

                    else {
                        return response.json({ success: false, message: 'passwords do not match' });
                    }
                });
                */

            }

        });

    }

});



router.post('/', function (request, response) {
    kortti.add(request.body, function (err, count) {
        if (err) {
            response.json(err);
        } else {
            response.json(request.body);
        }

    });
});


module.exports = router;