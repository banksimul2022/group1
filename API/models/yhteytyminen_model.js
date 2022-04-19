const db = require('../database');

const yhteytyminen = {
  
    add: function(yhteytyminen, callback) {
        return db.query(
          'insert into Asiakas_has_Tili (idAsiakas, idTili) values(?,?)',
          [yhteytyminen.idAsiakas, yhteytyminen.idTili], callback
        );
    }
    
}

module.exports = yhteytyminen; 