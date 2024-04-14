## リスト表示
> ansible-inventory -i hosts.yaml --list --yaml

## hostsの設定でコマンド実行
> ansible all -i hosts.yml -a "df -H"

## playbook実行
> ansible-playbook -i hosts.yml sample_play.yml
