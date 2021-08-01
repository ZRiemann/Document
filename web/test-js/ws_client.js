let wsUrl = 'ws://127.0.0.1/echo'
let ws = new WebSocket(wsUrl)

ws.onopen = function(event){
    console.log(`connection established to ${wsUrl}`, event)
    //ws.readyState = 1
}
ws.onclose = function(event){
    console.log(`${wsUrl} is closed now.`, event)
}
ws.onerror = function(event){
    console.log(`${wsUrl} error observed:`, event)
}
ws.onmessage = function(event){
    console.log(`${wsUrl} message received:`, event)
    console.log(event.timeStamp)
    console.log(event.type)

}