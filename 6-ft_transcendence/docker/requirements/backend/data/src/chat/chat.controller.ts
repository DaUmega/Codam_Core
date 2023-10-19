import { Controller, Get, Post, Body, Patch, Param, Delete, Put, ParseIntPipe } from '@nestjs/common';
import { ChatService } from './chat.service';
import ChannelDto from './dto/chat.dto';
import { AddUserDto } from './dto/add.dto';
import { DeleteUserDto } from './dto/delete.dto';

const apiKey = process.env.VUE_APP_SECRET;

@Controller(`${apiKey}/chat`)
export class ChatController {
  constructor(private readonly ChatService: ChatService) {}

  @Post('/')
  create(@Body() channel: ChannelDto) {
    return this.ChatService.createChannel(channel)
  }

  @Get("channel/:chatId")
  async getChannelInfo(
    @Param("chatId") channelId: number,
  ) {
    return this.ChatService.getChannelInfo(channelId)
  }

  @Get("user/:userId")
  async findAllChannels(
    @Param("userId") userId: number,
  ) {
    return this.ChatService.getChannelsList(userId)
  }

  @Get("public")
  async findPublicChannels() {
    return this.ChatService.getPublicChannels()
  }

  @Put(":id/add")
  async addUserToChannel(
    @Param("id", ParseIntPipe) id: number,
    @Body() user: AddUserDto,
  ) {
    return await this.ChatService.addUserToChat(
      id,
      user,
    )
  }

  @Put(":id/ban")
  async banUser(
    @Param("id", ParseIntPipe) id: number,
    @Body() user: DeleteUserDto,
  ) {
    return await this.ChatService.banUserToChat(
      id,
      user,
    )
  }

  @Put(":id/unban")
  async unbanUser(
    @Param("id", ParseIntPipe) id: number,
    @Body() user: DeleteUserDto,
  ) {
    return await this.ChatService.unbanUserToChat(
      id,
      user,
    )
  }

  @Delete(":id/delete")
  async deleteUserFromChannel(
    @Param("id", ParseIntPipe) id: number,
    @Body() user: DeleteUserDto,
  ) {
    return await this.ChatService.deleteUserFromChat(
      id,
      user,
    )
  }

  @Delete(":id/deletechannel")
  async deleteChannel(
    @Param("id", ParseIntPipe) id: number
  ) {
    return await this.ChatService.deleteChannel(id)
  }

  @Put(":id/makeadmin")
  async makeAdmin(
    @Param("id", ParseIntPipe) id: number,
    @Body() user: DeleteUserDto,
  ) {
    return await this.ChatService.makeUserAdmin(
      id,
      user,
    )
  }
}
