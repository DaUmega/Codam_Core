import {
  IsNotEmpty,
  MinLength,
} from 'class-validator'

export class MessageDto {

  @IsNotEmpty()
  channelId: number

  @IsNotEmpty()
  @MinLength(1, {
    message: "You can not send empty message",
  })
  text: string

  @IsNotEmpty()
  userId: number
}
