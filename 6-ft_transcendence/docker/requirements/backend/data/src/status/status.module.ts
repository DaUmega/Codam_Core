import { Module } from '@nestjs/common';
import { GateModule } from '../gate/gate.module';
import { StatusService } from './status.service';
import { StatusController } from './status.controller';
import { StatusGateway } from './status.gateway';   
import { GameStatusTrackerModule } from '../game/status/game.status.module';

@Module({
  imports: [
    GateModule,
    GameStatusTrackerModule,
  ],
  controllers: [StatusController],
  providers: [
    StatusService,
    StatusGateway,
  ],
  exports: [StatusService],
})
export class StatusModule {}