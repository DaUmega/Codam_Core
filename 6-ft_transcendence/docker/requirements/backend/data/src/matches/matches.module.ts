import { Module } from '@nestjs/common';
import { TypeOrmModule } from '@nestjs/typeorm';
import { Match } from './entities/match.entity';
import { MatchesController } from './matches.controller';
import { MatchesService } from './matches.service';

@Module({
  controllers: [MatchesController],
  imports: [TypeOrmModule.forFeature([Match])],
  providers: [MatchesService]
})
export class MatchesModule {}
