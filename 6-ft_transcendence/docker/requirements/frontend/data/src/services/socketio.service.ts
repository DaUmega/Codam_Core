import { io } from 'socket.io-client'

const siteIP = process.env.VUE_APP_SITE_IP

class SocketioService {
  socket: any

  // constructor () {
  //   // this.socket = io('http://localhost:3000') // TODO: Replace with .env
  // }

  setupSocketConnection (slashNameSpace: string) {
    console.log(`setupSocketConnection: ${slashNameSpace}`)
    this.socket = io(`http://${siteIP}:3000${slashNameSpace}`)
    // this.socket = io({
    //   path: ':3000',
    //   namespace: slashNameSpace,
    // })
    this.socket.on('connection_error', (err: any) => {
      console.log(`connection_error due to ${err.message}`)
    })
    this.socket.on('connect', () => {
      console.log('socket connected between backend and frontend')
    })
  }
}

export default SocketioService
