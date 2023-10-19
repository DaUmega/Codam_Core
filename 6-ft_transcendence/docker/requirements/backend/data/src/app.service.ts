import { Inject, Injectable } from '@nestjs/common'
import { SocketMappingService } from './gate/gate.service'

@Injectable()
export class AppService {
  constructor (
    @Inject('gameGate') private readonly gameGate: SocketMappingService
  ) {}
  getHello(): string {
    return 'Hello Nest!';
  }

  // list all game socket connections for testing
  async listSocketConnections() {
    console.log('gameGate connections: ')
    this.gameGate.logAllSocketAssociations()
  }
}
