import { Module } from '@nestjs/common';
import { TypeOrmModule } from '@nestjs/typeorm'
import { AppController } from './app.controller';
import { AppService } from './app.service';
import { UsersModule } from './users/users.module';
import { GameModule } from './game/game.module'
import { ChatModule } from './chat/chat.module'
import { MatchesModule } from './matches/matches.module'
import { AuthModule } from './auth/auth.module'
import { StatusModule } from './status/status.module';
import { GateModule } from './gate/gate.module';
import { ConfigModule } from '@nestjs/config';
import { ScheduleModule } from '@nestjs/schedule';

@Module({
  imports: [
    GameModule,
    ChatModule,
    UsersModule,
    StatusModule,
    GateModule,
    ConfigModule.forRoot({
      envFilePath: '../../../.env',
    }),
    TypeOrmModule.forRoot({
      type: 'postgres',
      host: process.env.SQL_HOSTNAME,
      port: 5432,
      username: process.env.POSTGRES_USER,
      password: process.env.POSTGRES_PASSWORD,
      database: process.env.POSTGRES_DB,
      autoLoadEntities: true,
      //lets TypeOrm automatically generate a SQL table from all classes with the @Entity() decorator and the metadata they contain.
      //synchronize is designed for development only, must DISABLE this feature in production.
      synchronize: true, 
    }),
    MatchesModule,
    AuthModule,
    ScheduleModule.forRoot()
  ],
  controllers: [AppController],
  providers: [AppService],
})
export class AppModule {}
