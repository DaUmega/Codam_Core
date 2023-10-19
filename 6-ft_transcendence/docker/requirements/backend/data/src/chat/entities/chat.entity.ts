import {
  Entity,
  Column,
  PrimaryGeneratedColumn,
  ManyToMany,
  OneToMany,
  JoinTable
} from 'typeorm'

import { User } from '../../users/entities/user.entity'
import { Message } from './message.entity'

@Entity()
export class Channel {
  @PrimaryGeneratedColumn()
  id: number

  @Column()
  name: string

  @Column({ default: true })
  isPublic: boolean

  @Column({ default: '' })
  password: string

  @ManyToMany(
    () => Message,
    {cascade: true}
  )
  @JoinTable()
  messages: Message[]

  @ManyToMany(
    () => User,
    {cascade: true}
  )
  @JoinTable()
  members: User[]

  @ManyToMany(
    () => User,
    {cascade: true}
  )
  @JoinTable()
  owners: User[]

  @ManyToMany(
    () => User,
    {cascade: true}
  )
  @JoinTable()
  administrators: User[]

  @ManyToMany(
    () => User,
    {cascade: true}
  )
  @JoinTable()
  banned: User[]

  @ManyToMany(
    () => User,
    {cascade: true}
  )
  @JoinTable()
  muted: User[]

}
