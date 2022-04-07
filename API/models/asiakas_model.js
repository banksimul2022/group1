const db = require('../database');

const asiakas = {
    
    get: function (callback) {
        return db.query('select * from Asiakas', callback);
    },
    getById: function (id, callback) {
        return db.query('select * from asiakas where idAsiakas=?', [id], callback);
    },
    add: function (asiakas, callback) {
        return db.query(
            'insert into Asiakas (Nimi, Osoite, Puhelinnumero) values(?,?,?)',
            [asiakas.Nimi, asiakas.Osoite, asiakas.Puhelinnumero], callback
        );
    }

}

module.exports = asiakas;