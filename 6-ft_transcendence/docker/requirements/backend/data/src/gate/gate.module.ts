import { Module } from '@nestjs/common';
import { SocketMappingService } from './gate.service';

@Module({
  imports: [],
  controllers: [],
  providers: [
    SocketMappingService,
    {
      provide: 'gameGate',
      useFactory: () => new SocketMappingService(),
      inject: [SocketMappingService],
    },
    {
      provide: 'statusGate',
      useFactory: () => new SocketMappingService(),
      inject: [SocketMappingService],
    },
  ],
  exports: ['gameGate', 'statusGate'],
})
export class GateModule {}