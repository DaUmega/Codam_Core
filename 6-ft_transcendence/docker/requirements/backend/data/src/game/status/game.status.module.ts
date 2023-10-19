import { Module } from '@nestjs/common';
import { StatusTracker } from './game.status';

@Module({
  imports: [],
  controllers: [
    
  ],
  providers: [
    StatusTracker,
    {
      provide: 'gameStatus',
      useFactory: () => new StatusTracker(),
      inject: [StatusTracker],
    },
    {
      provide: 'matchmakingStatus',
      useFactory: () => new StatusTracker(),
      inject: [StatusTracker],
    },
  ],
  exports: [
    'gameStatus',
    'matchmakingStatus',
  ],
})
export class GameStatusTrackerModule {}