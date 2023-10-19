import { Module } from '@nestjs/common';
import { ChatService } from './chat.service';
import { ChatController } from './chat.controller';
import { TypeOrmModule } from '@nestjs/typeorm';
import { User } from '../users/entities/user.entity';
import { Message } from './entities/message.entity';
import { Channel } from './entities/chat.entity';
import { UsersService } from '../users/users.service';
import { ChatGateway } from './chat.gateway'

@Module({
  imports: [
    TypeOrmModule.forFeature([
      User,
      Message,
      Channel
    ])
  ],
  controllers: [ChatController],
  providers: [
    UsersService,
    ChatService,
    ChatGateway
  ]
})
export class ChatModule {}
