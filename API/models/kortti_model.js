const db = require('../database');
const bcrypt = require('bcryptjs');

const saltRounds = 10;
const Kortti = {

  CheckifCardExists: function (Korttinumero, callback) {
    return db.query('select * from Kortti where Korttinumero=?', [Korttinumero], callback);
  },

  get: function (callback) {
    //do nothing
  },
  getPIN: function (Korttinumero, callback) { 
    return db.query('select PIN from Kortti where Korttinumero=?', [Korttinumero], callback);
  },
  addCard: function (Kortti, callback) { //add card
    bcrypt.hash(Kortti.PIN, saltRounds, function (err, hash) {
      return db.query('insert into Kortti (Korttinumero, PIN, Asiakas_IDAsiakas, Tili_idTili) values(?,?,?,?)',
        [Kortti.Korttinumero, hash, Kortti.Asiakas_IDAsiakas, Kortti.Tili_idTili], callback);
    })
  }

}

module.exports = Kortti;