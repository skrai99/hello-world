/*************************************************************************
 * Sample NodeJS Express launch script
 * Launches simple forward proxy which allows the customizer to quickly iterate
 * with changes without requiring to deploy to a full appserver of the awc.war
 * for development purpose.
 * 
 * Modify the URL object below to point to your deployed war file
 * 
 * One time must run npm install (assuming package.json contains express dev dependencies)
 *    this will load express and it's dependencies into your state/node_modules directory
 * 
 */
const express = require( 'express' );
const http = require( 'http' );
const httpProxy = require( 'http-proxy' );

const logger = require( process.env.JS_SCRIPTS + '/logger' );
const util = require( process.env.JS_SCRIPTS + '/util' );

var _warDir = process.env.ROOT + '/out/war';
var MSG_PREFIX = '  express: ';

const URL = {
    // Modify the following URL for your local deployment of the awc.war
    tc: 'http://localhost:7001',
    // Modify the following URL for your local deployment of the awc.war
    fsc: 'http://localhost:7001/aw',
    // Modify the following URL for your local deployment of the Vis Server
    vis: 'http://localhost:7001/VisProxyServlet',
    port: 3001
};

var app = express();
var server = http.Server( app );

var proxy = httpProxy.createProxyServer( { ws: true } );
app.route( '/tc/*' ).all( function( request, response ) {
    if( request.url.indexOf( '/logout' ) > -1 ) {
        response.cookie( 'JSESSIONID', 'LOGGED_OFF', { path: '/', httpOnly: true } );
    }
    logger.info( logger.nameColor( 'TC ' + request.method + ' ' ) + request.url );
    proxy.web( request, response, { target: URL.tc } );
} );

app.route( '/fms/*' ).all( function( request, response ) {
    logger.info( logger.nameColor( 'FSC ' + request.method + ' ' ) + request.url );
    proxy.web( request, response, { target: URL.fsc } );
} );

app.route( '/VisProxyServlet/*' ).all( function( request, response ) {
    logger.info( logger.nameColor( 'Vis ' + request.method + ' ' ) + request.url );
    proxy.web( request, response, { target: URL.vis } );
} );

proxy.on( 'error', function( error, req, res ) {
    logger.severe( 'proxy error\n' + error.toString(), MSG_PREFIX );
    if( !res.headersSent ) {
        res.writeHead( 500, { 'content-type': 'application/json' } );
    }

    var json = { error: 'proxy_error', reason: error.message };
    res.end( JSON.stringify( json ) );
} );

app.use( '/', express.static( _warDir, { index: 'tc.html' } ) );

logger.info( 'Starting Express @ ' + JSON.stringify( URL, null, 2 ), MSG_PREFIX );
_server = server.listen( URL.port, '0.0.0.0', null, function() {
    URL.port = _server.address().port;
    logger.success( 'Express app started @ ' + 'http://localhost:' + URL.port + ' OR http://' + process.env.COMPUTERNAME + ':' + URL.port, MSG_PREFIX );
} );
