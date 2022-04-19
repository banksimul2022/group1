const { query } = require('express');
const db = require('../database');

const toiminnot = {

    checkBalance: function (Korttinumero, callback) {
        return db.query('select Saldo from Tili join Kortti on Tili.idTili = Kortti.Tili_idTili where Korttinumero = ?', [Korttinumero], callback);
    },

    getInfo: function (Korttinumero, callback) {
        return db.query('select Nimi, Osoite, Puhelinnumero from Asiakas join Kortti on Asiakas.idAsiakas = Kortti.Asiakas_idAsiakas where Korttinumero = ?',
         [Korttinumero], callback);
    },
    Withdrawal: function (Kortinnumero, rahasumma) { //ei testattu
        identifiers = db.query('select idKortti, Tili_idTili from Kortti where Korttinumero = ?', [Kortinnumero], callback);
        retval = db.query('Insert into tilitapahtumat (Ajankohta, Tapahtuma, Summa, idTili, idKortti) values (now(), \'Nosto\', ?, ?, ? ) ', 
        [rahasumma], [identifiers[0].Tili_idTili], [identifiers[0].idKortti]);

        if (x) { //jos query ok
            return db.query('update Tili set Saldo = Saldo - ? where idTili = ?', [rahasumma], [identifiers[0].Tili_idTili]);
        }
        
    },
    getTransactions: function (Kortinnumero) {

    }

}


module.exports = toiminnot;