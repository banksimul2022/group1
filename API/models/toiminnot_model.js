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


    Withdrawal: function (rahasumma, TiliID, callback) {
        return db.query('update Tili set Saldo = Saldo - ? where idTili = ?', [rahasumma, TiliID], callback);
    },

    getTiliID: function (Kortinnumero, callback) {
        return db.query('select idKortti, Tili_idTili from Kortti where Korttinumero = ?', [Kortinnumero], callback);
    },

    //kesken ->
    AddTransaction: function (rahasumma, TiliID, KorttiID, callback) {
        
        return db.query('Insert into tilitapahtumat (Ajankohta, Tapahtuma, Summa, idTili, idKortti) values (now(), \'Nosto\', ?, ?, ? ) ',
            [rahasumma, TiliID, KorttiID]);
    },
    //kesken ->
    getTransactions: function (Kortinnumero) {

    }

}

module.exports = toiminnot;