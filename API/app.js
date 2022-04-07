var createError = require('http-errors');
var express = require('express');
var path = require('path');
var cookieParser = require('cookie-parser');
var logger = require('morgan');
const helmet = require('helmet');
const cors = require('cors');

const userRouter = require('./routes/user');
const korttiRouter = require('./routes/kortti');
const asiakasRouter = require('./routes/asiakas');
const tiliRouter = require('./routes/tili');
const yhteytyminenRouter = require('./routes/yhteytyminen');
const toiminnotRouter = require('./routes/toiminnot');
//const basicAuth = require('express-basic-auth');


var app = express();
//app.use(basicAuth({users: { 1 : 1}}))
app.set('view engine', 'ejs');

app.use(logger('dev'));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(express.static(path.join(__dirname + 'public')));
app.use(helmet());
app.use(cors());

app.use('/user', userRouter);
app.use('/kortti', korttiRouter);

app.use('/asiakas', asiakasRouter);
app.use('/tili', tiliRouter);
app.use('/yhteytyminen', yhteytyminenRouter);
app.use('/toiminnot', toiminnotRouter);

app.get('/', function(req, res) { //render homepage
  res.render('home');
});

module.exports = app;
