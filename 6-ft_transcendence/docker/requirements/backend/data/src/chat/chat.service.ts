import * as bcrypt from 'bcrypt';
import { HttpException, HttpStatus, Injectable } from '@nestjs/common';
import { Channel } from './entities/chat.entity'
import { Message } from './entities/message.entity'
import ChannelDto from './dto/chat.dto';
import { InjectRepository } from '@nestjs/typeorm';
import { Repository } from 'typeorm';
import { User } from '../users/entities/user.entity';
import { UsersService } from '../users/users.service';
import { AddUserDto } from './dto/add.dto';
import { DeleteUserDto } from './dto/delete.dto';
import { MessageDto } from './dto/message.dto';

@Injectable()
export class ChatService {
  constructor(
    @InjectRepository(Channel)
    private readonly channelRepository: Repository<Channel>,
    private readonly userService: UsersService,
  ) {}

  async createChannel(channel: ChannelDto) {

    // validate input
    const owner: User = await this.userService.findById(channel.ownerId)
    const errMsg: string = this.validateChannelData(channel, owner)
    if (errMsg.length)
      throw new HttpException(errMsg, HttpStatus.BAD_REQUEST)
    // create channel
    let hashedPw: string = ''
    if (channel.password.length)
      hashedPw = bcrypt.hashSync(channel.password, 12)
    const newChannel: Channel = new Channel()
    newChannel.owners = [owner]
    newChannel.administrators = [owner]
    newChannel.members = [owner]
    newChannel.name = channel.name.trim()
    newChannel.password = hashedPw
    newChannel.isPublic = !channel.private
    newChannel.banned = []
    newChannel.muted = []
    const channelRepo = this.channelRepository.create(newChannel)
    return await this.channelRepository.save(channelRepo)
  }

  validateChannelData(data: ChannelDto, user: User) : string {
    if (!user)
      return 'Invalid user'
    if (data.name.trim().length == 0)
      return 'Name can not be empty'
    return ''
  }

  async getChannelInfo(channelId: number) {
    const channel = await this.channelRepository.findOne({
      where: {
        id: channelId
      },
      relations: {
        messages: true,
        administrators: true,
        owners: true,
        members: true,
        muted: true,
        banned: true
      }
    })

    if (!channel)
      throw new HttpException('Invalid channel', HttpStatus.BAD_REQUEST)

    return channel
  }

  async getChannelsList(userId: number) {
    const user: User = await this.userService.findById(userId)
    if (!user)
      throw new HttpException('Invalid user', HttpStatus.BAD_REQUEST)

    const channels = await this.channelRepository.find({
      where: {
        members: {
          id: userId
        }
      },
      relations: {
        administrators: true,
        owners: true,
        members: true
      }
    })

    return channels
  }

  async getPublicChannels() {
    const channels = await this.channelRepository.find({
      where: {
        isPublic: true
      }
    })

    return channels
  }

  async addUserToChat(id:number, user:AddUserDto) {
    const channel = await this.getChannelInfo(id)
    // Check if banned
    if (channel.banned && channel.banned.some((member) => member.id === user.user)) {
      throw new HttpException("User is banned", HttpStatus.BAD_REQUEST)
    }
    // Check if already exists
    if (channel.members.some((member) => member.id === user.user)) {
      return channel;
    }

    const pwCheck = await bcrypt.compare(user.password.trim(), channel.password)
    if (!pwCheck && channel.password.length)
      throw new HttpException("Incorrect password", HttpStatus.BAD_REQUEST)

    const member = await this.userService.findById(user.user)
    channel.members.push(member)
    return this.channelRepository.save(channel)
  }

  async deleteUserFromChat(id:number, user:DeleteUserDto) {
    const channel = await this.getChannelInfo(id)

    let isAdmin: boolean = false
    channel.administrators.forEach( (admin) => {
      if (admin.id == user.adminId || user.adminId == user.deleteId)
        isAdmin = true
    })

    let isOwner: boolean = false
    if (channel.owners[0].id == user.adminId) {
      isOwner = true
    }

    if (isOwner && user.adminId != channel.owners[0].id) {
      const member = await this.userService.findById(user.deleteId)
      channel.members = channel.members.filter( (member) => member.id != user.deleteId)
      channel.administrators = channel.administrators.filter( (admin) => admin.id != user.deleteId)
      return this.channelRepository.save(channel)
    } else if (isAdmin) {
      if (channel.owners[0].id == user.deleteId) {
        throw new HttpException("You cannot kick the owner!", HttpStatus.BAD_REQUEST)
      }

      const member = await this.userService.findById(user.deleteId)
      channel.members = channel.members.filter( (member) => member.id != user.deleteId)
      channel.administrators = channel.administrators.filter( (admin) => admin.id != user.deleteId)
      return this.channelRepository.save(channel)
    } else {
      throw new HttpException("Insufficient Privilege", HttpStatus.BAD_REQUEST)
    }
  }

  async banUserToChat(id:number, user:DeleteUserDto) {
    const channel = await this.getChannelInfo(id)

    let isAdmin: boolean = false
    channel.administrators.forEach( (admin) => {
      if (admin.id == user.adminId)
        isAdmin = true
    })

    let isOwner: boolean = false
    if (channel.owners[0].id == user.adminId) {
      isOwner = true
    }

    if (user.adminId === user.deleteId) {
      throw new HttpException("You cannot ban yourself!", HttpStatus.BAD_REQUEST)
    } else if (isOwner) {
      const member = await this.userService.findById(user.deleteId)
      channel.members = channel.members.filter( (member) => member.id != user.deleteId)
      channel.administrators = channel.administrators.filter( (admin) => admin.id != user.deleteId)
      if (!channel.banned) {
        channel.banned = [];
      }
      channel.banned.push(member)
      return this.channelRepository.save(channel)
    } else if (isAdmin) {
      if (channel.owners[0].id == user.deleteId) {
        throw new HttpException("You cannot ban the owner!", HttpStatus.BAD_REQUEST)
      }

      const member = await this.userService.findById(user.deleteId)
      channel.members = channel.members.filter( (member) => member.id != user.deleteId)
      channel.administrators = channel.administrators.filter( (admin) => admin.id != user.deleteId)
      if (!channel.banned) {
        channel.banned = [];
      }
      channel.banned.push(member)
      return this.channelRepository.save(channel)
    } else {
      throw new HttpException("Insufficient Privilege", HttpStatus.BAD_REQUEST)
    }
  }

  async unbanUserToChat(id:number, user:DeleteUserDto) {
    const channel = await this.getChannelInfo(id)

    let isAdmin: boolean = false
    channel.administrators.forEach( (admin) => {
      if (admin.id == user.adminId)
        isAdmin = true
    })

    if (!isAdmin)
      throw new HttpException("Requested user is not an admin", HttpStatus.BAD_REQUEST);
    
      channel.banned = channel.banned.filter( (member) => member.id != user.deleteId)
      return this.channelRepository.save(channel)
  }

  async addMessageToChat(id:number, data:MessageDto) {
    const channel = await this.getChannelInfo(id)
    // Check if in channel or banned
    if (!channel.members.some((member) => member.id === data.userId) || (channel.banned && channel.banned.some((member) => member.id === data.userId))) {
      throw new HttpException("User is not in channel or banned", HttpStatus.BAD_REQUEST)
    }
    
    const user = await this.userService.findById(data.userId)
    
    const newMessage: Message = new Message()
    newMessage.createdAt = new Date()
    newMessage.sender = user
    newMessage.text = data.text
    console.log('check content:', newMessage)
    if (!channel.messages) {
      channel.messages = [];
    }
    channel.messages.push(newMessage)
    this.channelRepository.save(channel)
    return newMessage
  }

  async makeUserAdmin(id:number, user:DeleteUserDto) {
    const channel = await this.getChannelInfo(id)

    let isOwner: boolean = false
    channel.owners.forEach( (owner) => {
      if (owner.id == user.adminId)
        isOwner = true
    })

    if (isOwner) {
      const member = await this.userService.findById(user.deleteId)
      channel.administrators.push(member)
      return this.channelRepository.save(channel)
    } else {
      throw new HttpException("Insufficient privilege", HttpStatus.BAD_REQUEST)
    }
  }

  async deleteChannel(id:number) {
    return this.channelRepository.delete(id)
  }

  joinChannel() {}
  leaveChannel() {}

}
