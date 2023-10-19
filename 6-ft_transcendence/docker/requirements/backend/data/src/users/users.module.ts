import { Module } from '@nestjs/common';
import { TypeOrmModule } from '@nestjs/typeorm';
import { User } from './entities/user.entity';
import { FriendController } from './friend/friend.controller';
import { FriendService } from './friend/friend.service';
import { UsersController } from './users.controller';
import { UsersService } from './users.service';
import { BlockController } from './block/block.controller';
import { BlockService } from './block/block.service';

@Module({
  //forFeature() registers TypeOrm entites in this child module. forRoot() is only used once in AppModule. other module use forFeature().
  imports: [TypeOrmModule.forFeature([User])],
  controllers: [UsersController, FriendController, BlockController], //API routes that we want this module to instantiate.
  providers: [UsersService, FriendService, BlockService], //list of services that need to be instantiated by the Nest injector.
  exports: [UsersService]
})
export class UsersModule {}
