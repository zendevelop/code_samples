// module.js

var name;

exports.setName = function( thyName ) {
	name = thyName;
};

exports.sayHello = function() {
	console.log( 'Hello ' + name );
}


// getmodule.js
// another file
var myModule = require( './module' );
myModule.setName( 'BYVoid' );
myModule.sayHello();